# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)

Gem::Specification.new do |spec|
  spec.name          = "rbtelldus"
  spec.version       = `git tag | tail -1`
  spec.authors       = ["Patrik Pettersson"]
  spec.email         = ["pettersson.pa@gmail.com"]

  spec.summary       = %q{Small wrapper for telldus-core library. }
  spec.description   = %q{Write a longer description or delete this line.}
  spec.homepage      = "https://github.com/kaffepanna/rbtelldus"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]

  spec.extensions = ["ext/telldus/extconf.rb"]
  spec.add_development_dependency "bundler", "~> 1.7"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rspec"
end
