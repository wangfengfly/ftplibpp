/*
  This code snippet illustrates how to write data stream to ftp server files directly.
  author: wangfeng
  email: 985004673@qq.com
*/

int main(int argc,char **argv){
    ftplib* ftp = new ftplib();
    if(ftp->Connect(ftpaddress.c_str())){
        debug("ftp connect success\n");
    }
    else{
        delete ftp;

    }
    if(!ftp->Login("ftp", "")){
        fatal("ftp login failed.\n", ftp->LastResponse());
        ftp->Quit();//close the connection
        delete ftp;

    }
    ftp->Chdir(upload_path.c_str());
    //you can create directory on the ftp server directly
    if(!ftp->Chdir(output_path.c_str())){
        if(!ftp->Mkdir(output_path.c_str())){
            debug("%s.%s", output_path.c_str(), ftp->LastResponse());
        }
    }
    //assume output_file_tmp is the file that you want to write on the ftp server
    ftphandle* handle = ftp->RawOpen(output_file_tmp.c_str(), ftplib::filewriteappend, ftplib::ascii);
    if(!handle){
        ftp->Quit();
        delete ftp;
    }

    if(ftp->RawWrite(const_cast<char*>(send_data.c_str()), send_data.length(), handle) == -1){
        ftp->RawClose(handle);
        ftp->Quit();
        delete ftp;
    }

    if(!(ftp->RawClose(handle))){
        ftp->Quit();
        delete ftp;

    }

    ftp->Quit();
    delete ftp;
}
