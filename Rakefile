require "rake/extensiontask"
require 'bundler/gem_tasks'

Rake::ExtensionTask.new('telldus') do |ext|
  ext.name = 'telldus'                # indicate the name of the extension.
  ext.ext_dir = 'lib/telldus/ext/'         # search for 'hello_world' inside it.
  ext.lib_dir = 'lib/telldus/ext/'              # put binaries into this folder.
  ext.tmp_dir = 'tmp'                     # temporary folder used during compilation.
  #ext.source_pattern = "*.{c,cpp}"        # monitor file changes to allow simple rebuild.
  #ext.config_options << '--with-foo'      # supply additional options to configure script.
  #ext.gem_spec = spec                     # optionally indicate which gem specification                                          # will be used.
end

Rake::ExtensionTask.new('telldus_state') do |ext|
  ext.name = 'telldus_state'
  ext.ext_dir = 'spec/mocks/telldus-mock'
  ext.lib_dir = 'spec/mocks/telldus-mock/lib'

end

def run cmd
  output = `#{cmd}`
  raise output unless $? == 0
end

task :telldus_core_mock do
  Dir.chdir('spec/mocks/telldus-mock') do
    run "ruby extconf.rb > /dev/null"
    run "make"
    symlink "../telldus_state.so", "./lib/telldus_state.so", {force: true}
    symlink "../telldus_state.so", "./lib/libtelldus-core.so", {force: true}
    ENV['LD_LIBRARY_PATH']="spec/mocks/telldus-mock/lib:#{ENV['LD_LIBRARY_PATH']}"
  end
end

task :telldus_test_build => :telldus_core_mock do
  Dir.chdir('lib/telldus/ext/') do
    run "ruby extconf.rb --with-telldus-dir=../../../spec/mocks/telldus-mock"
    run "make"
  end
end

task :telldus_build do
  Dir.chdir('lib/telldus/ext') do
    run "ruby extconf.rb"
    run "make"
  end
end
task :test => [:telldus_test_build] do
  sh "rspec -f d"
end

#Rake::Task['bundle:build'].prerequisites << Rake::Task['telldus_test_build']


