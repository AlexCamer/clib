container_sources = files('stack.c', 'treemap.c', 'vector.c')
container_library = static_library(
    'container',
    container_sources,
    include_directories : project_includes,
    link_with : utility_library
)
