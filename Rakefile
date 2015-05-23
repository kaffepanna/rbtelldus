
namespace 'gem' do
  require 'bundler/gem_tasks'
end

def run cmd
  output = `#{cmd}`
  raise output unless $? == 0
end

namespace :compile do
  desc 'build telldus-core mock'
  task 'telldus_core' do
    Dir.chdir('spec/mocks/telldus-mock') do
      run "ruby extconf.rb > /dev/null"
      run "make"
      symlink "../telldus_state.so", "./lib/telldus_state.so", {force: true}
      symlink "../telldus_state.so", "./lib/libtelldus-core.so", {force: true}
      ENV['LD_LIBRARY_PATH']="spec/mocks/telldus-mock/lib:#{ENV['LD_LIBRARY_PATH']}"
    end
  end

  desc 'build rtelldus for testing'
  task 'telldus:test' => 'telldus_core' do
    Dir.chdir('ext/telldus') do
      run "ruby extconf.rb --with-telldus-dir=../../spec/mocks/telldus-mock"
      run "make"
    end
  end

  desc 'build telldus'
  task :telldus do
    Dir.chdir('lib/telldus/ext') do
      run "ruby extconf.rb"
      run "make"
    end
  end
end

desc 'run tests'
task :test => [:'compile:telldus:test'] do
  sh "rspec -f d"
end

