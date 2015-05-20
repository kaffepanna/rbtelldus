require 'rack/test'
require_relative '../api'

RSpec.configure do
  include Rack::Test::Methods
  def app() Telldus::Api end
end

describe Telldus::Api do
  describe '/devices' do
    before { get('/devices') }
    subject { last_response }

    it { expect(subject).to be_ok }
  end
end
