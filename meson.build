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

cc = meson.get_compiler('c')

lumina_include_directories = include_directories('include', 'include/widgets')

lumina_dependencies = []

if build_machine.system() == 'windows'
  lumina_dependencies += [
    cc.find_library('gdi32', required: true),
  ]
elif build_machine.system() == 'linux'
  lumina_dependencies += [
    dependency('xcb'),
    dependency('xcb-image'),
  ]
endif

lumina_sources = [
  # 'fonts/roboto_14.c',
  # 'fonts/roboto_20.c',

  'source/lumina_utf8.c',
  'source/lumina_text.c',
  'source/lumina_font.c',
  'source/lumina_color.c',
  'source/lumina_rectangle.c',

  'source/widgets/lumina_label.c',
  'source/widgets/lumina_button.c',
  'source/widgets/lumina_toggle_button.c',
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

# lumina_executable = executable(
#   'lumina',
#   sources: 'dev/main_win32.c',
#   link_with: lumina_library,
#   dependencies: lumina_dependency,
#   include_directories: lumina_include_directories,
# )
