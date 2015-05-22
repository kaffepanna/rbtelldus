# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)

Gem::Specification.new do |spec|
  spec.name          = "rtelldus"
  spec.version       = `git tag | tail -1`
  spec.authors       = ["Patrik Pettersson"]
  spec.email         = ["pettersson.pa@gmail.com"]

  spec.summary       = %q{Small wrapper for telldus-core library. }
  spec.description   = %q{Write a longer description or delete this line.}
  spec.homepage      = "https://github.com/kaffepanna/rtelldus"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]

  spec.extensions = ["lib/telldus/ext/extconf.rb"]
  spec.add_development_dependency "bundler", "~> 1.7"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rspec"
  spec.add_development_dependency "rack-test"
  spec.add_development_dependency 'rake-compiler', '~> 0.8.3'

  spec.add_runtime_dependency 'sinatra'
end
