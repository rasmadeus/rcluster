defineReplace(getSeparator) {
    win32: return(\\)
    unix: return(/)
}

defineReplace(joinPath) {
    return($$1$$getSeparator()$$2)
}

defineReplace(getConfig) {
    CONFIG(release, debug|release): return(release)
    CONFIG(debug, debug|release): return(debug)
}

defineReplace(pathToInstallator) {
    INSTALLATOR_PRO = $$joinPath($$(PRO_ROOT), $$joinPath(src, installator))
    PACKAGE_CORE = $$joinPath(packages, $$joinPath(core, data))
    return($$joinPath($$INSTALLATOR_PRO, $$PACKAGE_CORE))
}

defineReplace(copyToDestDir) {
    DST = $$1
    files = $$2

    mkpath($$DST)

    for(FILE, files) {
        win32:FILE ~= s,/,\\,g
        win32:DDIR ~= s,/,\\,g

        QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DST) $$escape_expand(\\n\\t)
    }

    export(QMAKE_POST_LINK)
    return(true)
}
