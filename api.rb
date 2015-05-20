require_relative 'lib/telldus.rb'
require 'sinatra/base'

module Telldus
  class Api < Sinatra::Base
    get '/devices' do
    end
  end
end
