container_library = library(
    'container',
    files(
        'array.c',
        'heap.c',
        'pool.c',
        'list.c'
    ),
    include_directories: project_includes,
    link_with: utility_library
)

test(
    'array',
    executable(
        'array_test',
        'array_test.c',
        include_directories: project_includes,
        link_with: container_library
    ),
    suite: 'container'
)

test(
    'heap',
    executable(
        'heap_test',
        'heap_test.c',
        include_directories: project_includes,
        link_with: [
            container_library,
            function_library
        ]
    ),
    suite: 'container'
)

benchmark(
    'heap',
    executable(
        'heap_bench',
        'heap_bench.c',
        include_directories: project_includes,
        link_with: [
            container_library,
            function_library
        ]
    ),
    suite: 'container'
)

test(
    'pool',
    executable(
        'pool_test',
        'pool_test.c',
        include_directories: project_includes,
        link_with: container_library
    ),
    suite: 'container'
)

benchmark(
    'pool',
    executable(
        'pool_bench',
        'pool_bench.c',
        include_directories: project_includes,
        link_with: [
            container_library,
            function_library
        ]
    ),
    suite: 'container'
)

test(
    'list',
    executable(
        'list_test',
        'list_test.c',
        include_directories: project_includes,
        link_with: container_library
    ),
    suite: 'container'
)
