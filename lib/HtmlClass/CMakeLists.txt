# ライブラリ名を定義
add_library(HTML_CLASS STATIC 
    src/htmlPage.cc src/htmlTag.cc 
)

target_include_directories(HTML_CLASS PUBLIC include)