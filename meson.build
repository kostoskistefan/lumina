project(
  'lumina',
  'c',
  version: '1.0.0',
  license: 'GPL',
  default_options: [
    'default_library=static',
    'warning_level=3',
  ],
)

lumina_include_directories = include_directories('include')

lumina_dependencies = [
  meson.get_compiler('c').find_library('m', required: true)
]

lumina_sources = [
  'source/lumina_color.c',
  'source/lumina_style.c',
  'source/lumina_render.c',
]

lumina_library = library(
  'lumina',
  sources: lumina_sources,
  dependencies: lumina_dependencies,
  include_directories: lumina_include_directories,
)

lumina_dependency = declare_dependency(
  link_with: lumina_library,
  include_directories: lumina_include_directories, 
)
