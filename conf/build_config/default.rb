MRuby::Build.new do |conf|
 # load specific toolchain settings
 conf.toolchain

 conf.gem :mgem => 'mruby-onig-regexp'
 # include the GEM box
 conf.gembox 'default'

 conf.enable_bintest
 conf.enable_test
end
