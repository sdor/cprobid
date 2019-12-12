#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <AminoAcidSeq.h>
#include <Ion.h>

using namespace std;
// using namespace swissprot;
using namespace bsoncxx;
using namespace protein;

int main(int argc, char** argv) {
    using builder::stream::document;
    using builder::stream::array;
    using builder::stream::open_document;
    using builder::stream::close_document;
    using builder::stream::finalize;

    std::string biosys_uri = std::getenv("BIOSYS_MONGO_URI");
    auto swissprot_xml = std::getenv("SWISSPROT_XML");

    mongocxx::instance instance{};
    mongocxx::uri uri(biosys_uri+"&maxPoolSize=4&minPoolSize=2");
    mongocxx::client client(uri);
    mongocxx::database db = client["biosys"];
    auto updateOptions = mongocxx::options::find_one_and_update();
    auto findOptions = mongocxx::options::find();
    updateOptions.upsert(true);
    findOptions.projection(document{} << "organism" << 1 << "peptide" << 1 << finalize);

    mongocxx::collection peptides = (db)["peptides"];
    mongocxx::collection precursors = (db)["precursors"];

    auto peptideCursor = peptides.find(document{} << finalize, findOptions);

    for(auto&& peptideDoc: peptideCursor) {
        auto organism = peptideDoc["organism"].get_utf8();
        auto peptide = peptideDoc["peptide"].get_utf8();
        auto aas = AminoAcidSeq { stdx::string_view(peptide).to_string()};
        auto mw = aas.monoisotopicMass();
        auto cidFragments = msms::cid(aas, 1);
        auto b_ions = bsoncxx::builder::basic::array{};
        for(const auto& ion: cidFragments.b_ions()) {
            b_ions.append(ion.mw());
        }
        auto y_ions = bsoncxx::builder::basic::array{};
        for(const auto& ion: cidFragments.y_ions()) {
            y_ions.append(ion.mw());
        }

        precursors.find_one_and_update(
            document{} << "peptide" << peptide << finalize,
            document{}
            << "$set" 
                << open_document
                    << "peptide" << peptide
                    << "mw" << mw
                    << "b_ions" << b_ions
                    << "y_ions" << y_ions
                << close_document
            << finalize,
            updateOptions
        );

        precursors.find_one_and_update(
            document{} << "peptide" << peptide << finalize,
            document{} << "$addToSet" << open_document << "organism" << organism << close_document << finalize
        );

    }

    return 0;
}