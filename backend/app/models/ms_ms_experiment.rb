class MsMsExperiment
  include Mongo::Document
  field :name, type: String
  field :description, type: String
  belongs_to :user
end
