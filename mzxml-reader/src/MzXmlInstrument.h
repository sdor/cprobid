#ifndef MzXML_Instrument_H
#define MzXML_Instrument_H
#include <string>
namespace MzXML {
  class Instrument {
      private:
      std::string manufacturer;
      std::string model;
      std::string ionization;
      std::string msType;
      public:
      Instrument(
        const std::string& manufacturer,
        const std::string& model,
        const std::string& ionization,
        const std::string& msType
      ) {
      this->manufacturer =           manufacturer;
      this->model        =    model;
      this->ionization   =         ionization;
      this->msType       =     msType;

      }

      std::string getManufacturer() const {return this->manufacturer;};
      std::string getModel() const {return this->model;};
      std::string getIonization() const {return this->ionization;};
      std::string getMsType() const {return this->msType;};

  };
}
#endif