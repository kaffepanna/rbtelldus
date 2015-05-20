task :telldus_core_mock do
  Dir.chdir('spec/mocks/telldus-mock') do
    sh "make"
    ENV['LD_LIBRARY_PATH']="spec/mocks/telldus-mock/lib:#{ENV['LD_LIBRARY_PATH']}"
  end
end

task :telldus_test_build => :telldus_core_mock do
  Dir.chdir('lib/telldus/ext/') do
    sh "ruby extconf.rb --with-telldus-dir=../../../spec/mocks/telldus-mock"
    sh "make"
  end
end

task :telldus_build do
  Dir.chdir('lib/telldus/ext') do
    sh "ruby extconf.rb"
    sh "make"
  end
end

task :test => [:telldus_test_build] do
  sh "rspec -f d"
end

