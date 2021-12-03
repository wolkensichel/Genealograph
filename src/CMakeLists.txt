set(TS_FILES Genealograph_de_DE.ts)

set(PROJECT_SOURCES
    mainwindow.cpp
    worksheet.cpp
    biographyeditor.cpp
    relationseditor.cpp
    treeobject.cpp
    relation.cpp
    partnershipinfo.cpp
    addpersondialog.cpp
    addpartnershipdialog.cpp
    adddescentdialog.cpp
    setupsheetdialog.cpp
    printsheetdialog.cpp
    iohandler.cpp
    biographylistitem.cpp
    relationslistitem.cpp
    partnershipinfolistitem.cpp
    clicklabel.cpp
    dockwidget.cpp
    ${TS_FILES}
)

add_executable(Genealograph
    main.cpp
    ${PROJECT_SOURCES}
)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(Genealograph PRIVATE Qt6::Widgets Qt6::PrintSupport)
