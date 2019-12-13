Rails.application.routes.draw do
  resources :ms_ms_experiments
  devise_for :users, :controllers => {
    sessions: 'sessions',
    registrations: 'registrations'
  }, defaults: { format: :json }
  # mount_devise_token_auth_for 'User', at: 'auth'
  # For details on the DSL available within this file, see https://guides.rubyonrails.org/routing.html
end
