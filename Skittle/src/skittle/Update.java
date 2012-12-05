package skittle;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.LineNumberReader;
import java.net.URL;
import java.net.URLConnection;
import java.nio.charset.MalformedInputException;
import java.security.DigestInputStream;
import java.security.MessageDigest;
import javax.swing.JOptionPane;

/**
 * The Updater for Skittle
 * 
 * Checks to see if there are updates available.
 * This is done by downloading the latest files.list 
 * and comparing the file MD5 that are listed.
 * 
 * If updates are available and the action is request, 
 * all new files will be downloaded.
 * 
 * @author bryan
 */
public class Update implements Runnable {
    /**
     * The path to the user install area for Skittle
     */
    private File skittlePath;
    
    /**
     * The parent MainWindow that started the install process
     */
    private MainWindow window;
    
    /**
     * What OS we are running on
     */
    private static String OS = null;
    
    /**
     * Constructor for the Update object
     * 
     * @param window The parent MainWindow that started the update process
     */
    public Update(MainWindow window, String OS){
        this.OS = OS;
        
        //Set the path to the skittle install folder
        String skittlePathString = null;
        
        if(isWindows()){
            skittlePathString = System.getProperty("user.home") + "/AppData/Roaming/Skittle/";
        }
        else if(isMac()){
            skittlePathString = "/Applications/SkittleToo.app";
        }
        skittlePath = new File(skittlePathString);
        
        this.window = window;
    }
    
    @Override
    public void run(){
        //Do nothing until an action is requested
    }
    
    /**
     * Download the files.list from the server
     * then compare file MD5 to see if an update is available.
     * 
     * @return If there is an update available
     */
    public boolean CheckForUpdates(){
        boolean update = false;
        
        //Download the current file listing
        downloadFile("files.list");
        String filesList = skittlePath + "/" + "files.list";
        String fileInfo;
        String[] fileInfoSplit;
        
        try{
            //Go through each file in the list and compare version numbers
            FileInputStream fis = new FileInputStream(filesList);
            
            DataInputStream in = new DataInputStream(fis);
            BufferedReader br = new BufferedReader(new InputStreamReader(in));
            
            while((fileInfo = br.readLine()) != null){
                //Split the file name from the file version
                fileInfoSplit = fileInfo.split(" ");
                
                //Make sure that the listed file exists, then continue
                if(new File(skittlePath + "/" + fileInfoSplit[2]).exists()){
                    //Generate an MD5 of the local file and compare to remote MD5
                    MessageDigest md = MessageDigest.getInstance("MD5");
                    String localHash = getMD5(new FileInputStream(skittlePath + "/" + fileInfoSplit[2]), md, 2048);
                    
                    if(localHash.compareTo(fileInfoSplit[0]) != 0){
                        //Hashes aren't equal, so there is an update
                        update = true;
                        break;
                    }
                }
                else{
                    //Remote file doesn't exist locally, so there is an update
                    update = true;
                    startUpdateNow();
                    break;
                }
            }
        }
        catch(Exception e){
            JOptionPane.showMessageDialog(window, "Error checking for updates. \n" + e.getMessage(), "Error!", JOptionPane.ERROR_MESSAGE);
            System.exit(2);
        }
        
        return update;
    }
    
    /**
     * Download the files listing, check to see if there is an update,
     * then download new file if needed.
     */
    public void DoUpdates(){
        //Download the current file listing
        downloadFile("files.list");
        String filesList = skittlePath + "/" + "files.list";
        int numberOfFiles;
        int percentInterval;
        String fileInfo;
        String[] fileInfoSplit;
        
        try{
            //Count the number of files to be checked
            //Count the number of files to be downloaded
            LineNumberReader lnr = new LineNumberReader(new FileReader(filesList));
            lnr.skip(Long.MAX_VALUE);
            numberOfFiles = lnr.getLineNumber();
            
            //Calculate percent update per file
            percentInterval = 100 / numberOfFiles;
            
            //Go through each file in the list and compare version numbers
            FileInputStream fis = new FileInputStream(filesList);
            
            DataInputStream in = new DataInputStream(fis);
            BufferedReader br = new BufferedReader(new InputStreamReader(in));
            
            while((fileInfo = br.readLine()) != null){
                //Split the file name from the file version
                fileInfoSplit = fileInfo.split(" ");
                
                //Make sure that the listed file exists, then continue
                if(new File(skittlePath + "/" + fileInfoSplit[2]).exists()){
                    //Generate an MD5 of the local file and compare to remote MD5
                    MessageDigest md = MessageDigest.getInstance("MD5");
                    String localHash = getMD5(new FileInputStream(skittlePath + "/" + fileInfoSplit[2]), md, 2048);
                    
                    if(localHash.compareTo(fileInfoSplit[0]) != 0){
                        //Hashes aren't equal, so there is an update
                        downloadFile(fileInfoSplit[2]);
                    }
                }
                else{
                    //Remote file doesn't exist locally, so there is an update
                    downloadFile(fileInfoSplit[2]);
                }
                
                window.SetProgressBarPercent(window.GetProgressBarPercent() + percentInterval);
            }
        }
        catch(Exception e){
            JOptionPane.showMessageDialog(window, "Error performing update. \n" + e.getMessage(), "Error!", JOptionPane.ERROR_MESSAGE);
            System.exit(2);
        }
        
        window.ChangeInstallState(true);
        window.Launch(false);
    }
    
    /**
     * Call back to the main window to launch the update process NOW.
     */
    private void startUpdateNow(){
        window.DoUpdates();
    }
    
    /**
     * Function to grab a specified file from the server via http
     * 
     * @param filename the name of the file to pull from the Skittle server
     */
    private void downloadFile(String filename){
        //Setup the URL to begin grabbing files from the server
        String skittleServer = "http://josiah.newlinetechnicalinnovations.com/skittle/";
        URL url;
        URLConnection con;
        int i;
        
        //Get the file list from the server
        File file;
        try{
            url = new URL(skittleServer + filename);
            con = url.openConnection();
            
            if(filename.compareToIgnoreCase("Skittle.exe") !=0){
                file = new File(skittlePath + "/" + filename);
            }
            else{
                file = new File(skittlePath + "/" + "SkittleTemp.exe");
            }
            BufferedInputStream bis = new BufferedInputStream(con.getInputStream());
            //BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(file.getName()));
            BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(file));
            
            while((i = bis.read()) != -1){
                bos.write(i);
            }
            bos.flush();
            bos.close();
            bis.close();
        }
        catch(MalformedInputException e){
            JOptionPane.showMessageDialog(window, "Malformed Packet when downloading a file during update. \n" + e.getMessage(), "Error!", JOptionPane.ERROR_MESSAGE);
            System.exit(2);
        }
        catch(IOException e){
            JOptionPane.showMessageDialog(window, "Error writing downloaded file during update. \n" + e.getMessage(), "Error!", JOptionPane.ERROR_MESSAGE);
            System.exit(2);
        }
        catch(Exception e){
            
        }
    }
    
    /**
     * Generate the MD5 of the given file,
     * convert it to Hex,
     * and return as a string
     * 
     * @param is The input stream that is reading the file to be summed
     * @param md MessageDigest set to the hash type you want
     * @param byteArraySize 2048
     * @return The calculated and converted hash sum
     */
    private String getMD5(InputStream is, MessageDigest md, int byteArraySize){
        md.reset();
        byte[] bytes = new byte[byteArraySize];
        int numBytes;
        try{
            while((numBytes = is.read(bytes)) != -1){
                md.update(bytes, 0, numBytes);
            }
        }
        catch(Exception e){
            JOptionPane.showMessageDialog(window, "Error generating MD5 sum during update check. \n" + e.getMessage(), "Error!", JOptionPane.ERROR_MESSAGE);
        }
        byte[] digest = md.digest();
        //String result = new String(Hex.encodeHex(digest));
        StringBuffer hex = new StringBuffer();
        for(int i = 0; i < digest.length; i++){
            hex.append(Integer.toString((digest[i] & 0xFF) + 0x100, 16).substring(1));
        }
        return hex.toString();
    }
    
    public static boolean isWindows(){
        return OS.startsWith("Windows");
    }
    
    public static boolean isMac(){
        return OS.startsWith("Mac");
    }
}
