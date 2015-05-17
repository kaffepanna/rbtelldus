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

			it { is_expected.to be_true }
			it { expect(switch_state.on).to eq(true) }
		end

		context 'when device does not support on' do
      let!(:id) { 1 }
      before {switch_state.supported_methods = 0 }
			it { is_expected_to raise_error(NotSupportedException) }
		end
	end

  describe '#off' do
    context 'when device support turning off' do
			let!(:id) { 1 }

			it { is_expected.to be_true }
			it { expect(switch_state.off).to eq(true) }
		end

		context 'when device does not support off' do
      let!(:id) { 1 }
      before {switch_state.supported_methods = 0 }
			it { is_expected_to raise_error(NotSupportedException) }
		end

	end

	describe '.get_device' do
    subject(:device) { Device.get_device(id) }

		context "when device is configured" do
		  let!(:id) { 1 }

			it { is_expected.to be_kind_of(Device) }
		end

    context "when device i not configured" do
      let!(:id) { 2 }
      it { is_expected_to raise_error(DeviceNotFoundException) }
    end
	end
end

