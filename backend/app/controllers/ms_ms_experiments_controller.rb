class MsMsExperimentsController < ApplicationController
  respond_to :json
  before_action :authenticate_user!
  def index
    p @current_user
    @experiments = @current_user.ms_ms_experiments
    render json: @experiments
  end
end
