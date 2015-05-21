verbose(false)

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

