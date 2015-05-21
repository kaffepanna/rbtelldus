require 'mkmf'

extension_name = 'telldus_state'

dir_config("telldus-core", './include', './lib')

create_makefile(extension_name)
