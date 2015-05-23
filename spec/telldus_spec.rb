
puts "Load path #{$:}"
require_relative './mocks/telldus-mock/lib/telldus_state'
require 'rbtelldus'


shared_examples 'a controll function' do |args|
  method =  args[:method]
  argument = args[:arg]

  let(:id) { 1 }
  let!(:state) { TelldusSwitchState.new id: 1 }
  subject { described_class.send(method, id, *argument) }

  context 'device is configured' do
    let!(:id) { 1 }
    context "and supports .#{method}" do
      it { expect(subject).to eq(Telldus::SUCCESS) }
      it { expect_to_change }
    end

    context "and does not support .#{method}" do
      let!(:state) { TelldusSwitchState.new id: 1, supported_methods: 0 }
      it { expect(subject).to eq(Telldus::METHOD_NOT_SUPPORTED) }
    end
  end
  context 'device is not configured' do
    let(:id) { 2 }
    it { expect(subject).to eq(Telldus::NOT_FOUND) }
  end
end

describe Telldus do
  before(:each) { TelldusState.clear  }

	describe '.on' do
    it_behaves_like 'a controll function', method: :on do
      let(:expect_to_change) { expect{subject}.to change{state.on}.to(true) }
    end
	end

  describe '.off' do
    it_behaves_like 'a controll function', method: :off do
      let!(:state) { TelldusSwitchState.new id: 1, on: true }
      let(:expect_to_change) { expect{subject}.to change{state.on}.to(false) }
    end
	end

  describe '.dim' do
    it_behaves_like 'a controll function', method: :dim, arg:25 do
      let(:expect_to_change) { expect{subject}.to change{state.dim}.to(25) }
    end
  end

  describe '.learn' do
    it_behaves_like 'a controll function', method: :learn do
      let(:expect_to_change) { expect{subject}.to change{state.learning}.to(true) }
    end
  end

  describe '.getName' do
    subject { Telldus.getName(id) }

    context 'when device is configured' do
      let(:id) { 1 }
      let!(:device) { TelldusSwitchState.new id: id, name: 'Kitchen' }

      it { expect(subject).to eq('Kitchen') }
    end

    context "when device is not configured" do
      let(:id) { 1 }
      it { expect(subject).to eq('') }
    end
  end

  describe '.setName' do
    let(:name) { 'Living room' }
    subject { Telldus.setName(id, name) }

    context 'when device is configured' do
      let(:id) { 1 }
      let!(:device) { TelldusSwitchState.new id: id, name: 'Kitchen' }
      it { expect(subject).to eq(true) }
      it { expect{subject}.to change{device.name}.from('Kitchen').to(name) }
    end

    context 'when device is unconfigured' do
      let(:id) { 1 }
      it { expect(subject).to eq(false) }
    end
  end

  describe '.lastCommand' do
    let(:id) { 1 }
    let(:mask) { Telldus::TURNON | Telldus::TURNOFF }
    subject { Telldus.lastCommand(id, mask) }
    context 'when client support last command' do
      let!(:device) { TelldusSwitchState.new id: id, last_command: Telldus::TURNON }
      it { expect(subject).to eq(Telldus::TURNON) }
    end

    context "when client does not support last command" do
      let!(:device) { TelldusSwitchState.new id: id, last_command: Telldus::DIM }
      it { expect(subject).to eq(0) }
    end
  end

  describe '.lastValue' do
    let(:last_value) { 128 }
    let(:id) { 1 }
    let!(:device) { TelldusSwitchState.new id: id, dim: last_value }

    subject { Telldus.lastValue(id) }

    it { expect(subject).to eq(last_value) }
  end

  describe '.create' do
    let(:new_id) { 1 }
    subject { Telldus.create }
    it { expect(subject).to eq(new_id) }
    it { expect{subject}.to change{TelldusState.has_key?(new_id)}.from(false).to(true) }
  end

  describe '.remove' do
    let(:id) { 1 }
    subject { Telldus.remove id }
    context 'when device is configured' do
      let!(:device) { TelldusSwitchState.new id: id }
      it { expect(subject).to eq(true) }
      it { expect{subject}.to change{TelldusState.has_key?(id)}.from(true).to(false) }
    end

    context 'when device is not configured' do
      it { expect(subject).to eq(false) }
    end
  end

  describe '.getParam' do
    let(:id) { 1 }
    let(:name) { 'house' }
    let(:value) { 'A' }
    subject { Telldus.getParam id, name, 'default' }

    context 'when parameter is set' do
      let!(:device) { TelldusSwitchState.new id: id, params: { name => value  } }
      it { expect(subject).to eq(value) }
    end

    context 'when parameter is not set' do
      let!(:device) { TelldusSwitchState.new id: id }
      it { expect(subject).to eq('default') }
    end
  end

  describe '.setParam' do
    let!(:id) { 1 }
    let(:name) { 'house' }
    let(:value) { 'A' }
    let!(:device) { TelldusSwitchState.new id: id }
    subject { Telldus.setParam id, name, value }
    it { expect(subject).to eq(true) }
    it { expect{subject}.to change{device.params.has_key?(name)}.to(true) }
  end

  describe '.setModel' do
    let(:id) { 1 }
    let(:model) { 'codeswitch' }
    let!(:device) { TelldusSwitchState.new id: id }
    subject { Telldus.setModel(id, model) }
    
    it { expect(subject).to eq(true) }
    it { expect{subject}.to change{device.model}.to(model) }
  end

  describe '.getModel' do
    let(:id) { 1 }
    let(:model) { 'codeswitch' }
    let!(:device) { TelldusSwitchState.new id: id, model: model }
    subject { Telldus.getModel(id) }
    
    it { expect(subject).to eq(model) }
  end
end

