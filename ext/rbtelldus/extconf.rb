# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

# Give it a name
extension_name = 'rbtelldus/rbtelldus'

dir_config("telldus")

# Add telldus library link
unless have_library('telldus-core')
  raise
end


# Do the work
create_makefile(extension_name)
