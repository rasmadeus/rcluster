import os
import shutil
import subprocess
import sys

def copy_files(src_dir, dst_dir, extensions):
    if not os.path.exists(dst_dir):
        os.makedirs(dst_dir)
        
    for file_name in os.listdir(src_dir):
        file_extension = os.path.splitext(file_name)[1]
        if file_extension in extensions:
            src_file_name = os.path.join(src_dir, file_name)
            dst_file_name = os.path.join(dst_dir, file_name)
            if os.path.isfile(dst_file_name):
                print("Skip", file_name, "due to one already exists")
            else:
                print("Copy", file_name)
                shutil.copyfile(src_file_name, dst_file_name)

def copy_files_by_name(src_dir, dst_dir, file_names):
    if not os.path.exists(dst_dir):
        os.makedirs(dst_dir)
        
    for file_name in os.listdir(src_dir):
        if file_name in file_names:
            src_file_name = os.path.join(src_dir, file_name)
            dst_file_name = os.path.join(dst_dir, file_name)
            if os.path.isfile(dst_file_name):
                print("Skip", file_name, "due to one already exists")
            else:
                print("Copy", file_name)
                shutil.copyfile(src_file_name, dst_file_name) 

def boost_lib(config, lib):
    return 'boost_' + lib + '-vc141-mt-gd-x32-1_68.dll' if config == 'debug' else 'boost_' + lib + '-vc141-mt-x32-1_68.dll'      

def windeploy(src_dir, dst_dir, extensions):
    files = [f for f in os.listdir(src_dir) if os.path.isfile(os.path.join(src_dir, f)) and os.path.splitext(f)[1] in extensions]
    for file_name in files:
        file_path = os.path.join(src_dir, file_name)
        subprocess.check_output('windeployqt.exe --dir ' + dst_dir + ' --compiler-runtime --no-translations ' + file_path)

def windeploy_qml(dst_dir, file_infos):
    for file_info in file_infos:
        qml_dir = file_info['qml_dir']
        bin_path = file_info['bin_path']
        subprocess.check_output('windeployqt.exe --dir ' + dst_dir + ' --compiler-runtime --no-translations ' + '--qmldir ' + qml_dir + ' ' + bin_path)

def main():
    config = sys.argv[1]
    dst_dir = sys.argv[2]
    out_dir = os.path.join(os.environ['OUT_DIR'], config)
    qt_dir = os.environ['QT_DIR']
    gstreamer_dir = os.environ['GSTREAMER_HOME']
    zlib_dir = os.environ['ZLIB_HOME']
    quazip_dir = os.environ['QUAZIP_HOME']
    boost_dir = os.environ['BOOST_HOME']
    vcinstalldir = os.environ['VSINSTALLDIR']
    tm_dir = os.environ['TM_LIBS']
    pro_root = os.environ['PRO_ROOT']

    print("Out dir", out_dir)

    if config == 'release':
        copy_files(out_dir, dst_dir, ('.exe', '.dll',))
        copy_files(os.path.join(out_dir, 'plugins'), os.path.join(dst_dir, 'plugins'), ('.dll',))

    windeploy(dst_dir, dst_dir, ('.exe',))
    windeploy(os.path.join(dst_dir, 'plugins'), dst_dir, ('.dll',))
    windeploy_qml(dst_dir, (
        {'qml_dir' : os.path.join(pro_root, 'src/plugins/calib_viewer/res'), 'bin_path' : os.path.join(out_dir, 'plugins/calib_viewer.dll'),},
    ))

    copy_files(os.path.join(gstreamer_dir, 'bin'), dst_dir, ('.dll',))
    copy_files(os.path.join(gstreamer_dir, 'lib/gstreamer-1.0'), os.path.join(dst_dir, 'gst_plugins'), ('.dll',))
    copy_files(os.path.join(zlib_dir, os.path.join('lib', config)), dst_dir, ('.dll',))
    copy_files(os.path.join(quazip_dir, os.path.join('lib', config)), dst_dir, ('.dll',));
    copy_files_by_name(os.path.join(boost_dir, 'lib'), dst_dir, (
        boost_lib(config, 'system'),
        boost_lib(config, 'date_time'),
        boost_lib(config, 'filesystem'),
        boost_lib(config, 'thread'),
        boost_lib(config, 'log'),
        boost_lib(config, 'log_setup'),
        boost_lib(config, 'regex'),        
    ))
    copy_files(os.path.join(tm_dir, 'dlls'), dst_dir, ('.dll', '.ini',))
    copy_files(os.path.join(tm_dir, config), dst_dir, ('.dll',))

if __name__ == '__main__':
    main()
    
