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

lumina_include_directories = [
  include_directories('fonts'),
  include_directories('include'),
]

lumina_dependencies = [
  meson.get_compiler('c').find_library('m', required: true)
]

lumina_sources = [
  'source/graphics/lumina_circle.c',
  'source/graphics/lumina_line.c',
  'source/graphics/lumina_rectangle.c',
  'source/graphics/lumina_text.c',
  'source/lumina_color.c',
  'source/lumina_font.c',
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

if get_option('compile_dev_executable')
  lumina_dev_sources = [
    'dev/main.c',
    'fonts/dev_font.c',
  ]

  lumina_dev_dependencies = [
    lumina_dependency,
    dependency('xcb'),
    dependency('xcb-image'),
  ]

  lumina_dev_executable = executable(
    'lumina-dev',
    sources: lumina_dev_sources,
    link_with: lumina_library,
    dependencies: lumina_dev_dependencies,
  )
endif
