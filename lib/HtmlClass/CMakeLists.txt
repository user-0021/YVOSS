# ライブラリ名を定義
add_library(HTML_CLASS STATIC 
    src/html_class.cc
)

target_include_directories(HTML_CLASS PUBLIC include)