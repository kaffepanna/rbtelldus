require_relative './mocks/telldus-mock/lib/telldus_state'
require_relative '../lib/telldus/telldus'

include Telldus

describe Device do
	let!(:state) { TelldusState }
	let!(:switch_state) {TelldusState[id]}
	before(:context) { TelldusState[1] = TelldusSwitchState.new id: 1, name: 'Living Room' }

	describe '#on' do
		subject(:device) { Device.get_device(id).on }
		
		context 'when device support turning on' do
			let!(:id) { 1 }

			it "Returns true" do
				is_expected.to be_true
			end
			
			it "Turns on light" do
				expect(switch_state.on).to eq(true)
			end
		end

		context 'when device does not support on' do
			it "should return false"
		end
	end

	describe '.get_device' do
		subject(:device) { Device.get_device(id) }
		let!(:id) { 1 }

		context "when device is configured" do
			it "Should return a device" do
				is_expected.to be_kind_of(Device)
			end
		end
	end
end

