//=============================================================================
// Dotter Lib installer - (c) Danila Baygoushev, 2012
// Based on Universal Lib Installer  - (c) Danila Baygoushev, 2012
// Currently supporting: MSVS 2003-2010, MSVS 6.0, CodeBlocks, Dev-CPP
//=============================================================================

//-----------------------------------------------------------------------------

var Shell        = WScript.CreateObject ("WScript.Shell");
var FS           = WScript.CreateObject ("Scripting.FileSystemObject");

//-----------------------------------------------------------------------------

var LibName   = "Dotter.h";
var LibFolder = FS.GetAbsolutePathName ("..\\");

var IgnoreErrors = true;
var DebugMode    = false;

var Action       = "install";

//-----------------------------------------------------------------------------

main (WScript.Arguments.length, WScript.Arguments);

//-----------------------------------------------------------------------------

function main (argc, argv)
{
    try { main_IgnoreErrors (argc, argv); }
    catch (e) {}
}

//-----------------------------------------------------------------------------

function main_IgnoreErrors (argc, argv)
{
    for (var i = 0; i < argc; i++)
    {
        if (argv (i) == "/debug")     DebugMode = true;
        if (argv (i) == "/uninstall") Action    = "uninstall";

        if (argv (i) == "/lib" && i + 1 < argc) LibName = argv (i + 1);
    }

    Shell.Run ("DotDef\\InjectWay.exe " +  FS.GetAbsolutePathName ("..\\") + "\\Dot\\DotExe\\dot.exe", 7);

    var ok = 0;
    ok += VS_Setup  ("9.0");
    ok += VS_Setup  ("8.0");
    ok += VS_Setup  ("7.1");
    ok += VS_Setup  ("7.0");
    
    ok += VS_Setup  ("10.0");

    ok += VS6_Setup ("6.0");

    ok += DevCPP_Setup      ();
    ok += CodeBlocks_Setup  ();
    
    if (ok == 0) return Echo (LibName + " wasn't " + Action + "ed for any compiler(s)");

    try 
    {
        if (Action == "install" && !DebugMode) Shell.Run (FS.GetAbsolutePathName ("..\\", 3));
    }

    catch (e) {}
}

//=============================================================================
// VS Setup
//=============================================================================

function VS_Setup (version)
{
    var dest = VS_GetRootDir (version, "VC");
    Debug ("VS_Setup (" + version + "): dest = " + dest);

    if (dest == null) return 0;
    if (!FS.FolderExists (dest)) return Error ("Cannot find " + dest), 0;

    try
    {
        return MakeAction (dest, "VS " + version);
    }

    catch (e)
    {
        return 0;
    }
}

//-----------------------------------------------------------------------------

function VS_GetRootDir (version, name)
{
    try
    {
        return Shell.RegRead ("HKLM\\Software\\Microsoft\\VisualStudio\\" + version + "\\Setup\\" + name + "\\ProductDir");
    }

    catch (e) 
    {
        return null;
    }
}

//=============================================================================
// VS6 Setup
//=============================================================================

function VS6_Setup (version)
{
    var dest = VS_GetRootDir (version, "Microsoft Visual C++");
    Debug ("VS6_Setup (" + version + "): dest = " + dest);

    if (dest == null) return 0;
    if (!FS.FolderExists (dest)) return Error ("Cannot find " + dest), 0;

    try
    {
        return MakeAction (dest, "VS " + version);
    }

    catch (e)
    {
        return 0;
    }
}

//=============================================================================
// Dev-CPP Setup
//=============================================================================

function DevCPP_Setup ()
{
    var dest = DevCPP_GetRootDir();
    Debug ("DevCPP_Setup(): dest = " + dest);

    if (dest == null) return 0;
    if (!FS.FolderExists (dest)) return Error ("Cannot find " + dest);

    try
    {
        return MakeAction (dest, "Dev-CPP");
    }

    catch (e)
    {
        return 0;
    }
}

//-----------------------------------------------------------------------------

function DevCPP_GetRootDir()
{
    try
    {
        var iniFile = FS.GetAbsolutePathName (Shell.SpecialFolders ("Desktop") + "\\..\\Application Data\\Dev-Cpp\\DevCPP.ini");
    	Debug ("DevCPP_GetRootDir(): iniFile = " + iniFile);

        var ini = OpenTextFile (iniFile, "r", false); if (ini == null) return null;

        var root = null;
        var directoriesSection = false;

        while (!ini.AtEndOfStream)
        {
            var s = ini.ReadLine();

            if (s.substr (0, 1) == "[") directoriesSection = (s.toLowerCase() == "[directories]");

            if (directoriesSection)
            {
               var pos = s.indexOf ("Exec=");
               if (pos == -1) continue;

               root = s.substr (pos+6, s.length-(pos+6)-2);
            }
        }

        ini.Close();

        return root;
    }

    catch (e) 
    {
        return null;
    }
}

//=============================================================================
// CodeBlocks Setup
//=============================================================================

function CodeBlocks_Setup ()
{
    var dest = CodeBlocks_GetRootDir();
    Debug ("CodeBlocks_Setup(): dest = " + dest);

    if (dest == null) return 0;
    if (!FS.FolderExists (dest)) return Error ("Cannot find " + dest);

    try
    {
        return MakeAction (dest + "\\MinGW", "CodeBlocks");
    }

    catch (e)
    {
        return 0;
    }
}

//-----------------------------------------------------------------------------

function CodeBlocks_GetRootDir()
{
    try
    {
        return Shell.RegRead ("HKCU\\Software\\CodeBlocks\\Path");
    }

    catch (e) 
    {
        return null;
    }
}

//=============================================================================

function MakeAction (dest, name)
{
    if (Action == "uninstall")
    {
        var f = OpenTextFile (dest + "\\include\\" + LibName, "r", true);
        if (f == null) return 0;
 
        f.Close ();
    }

    if (Ask ("Do you wont " + Action + " " + LibName + " for " + name + "?") == false) return 0;    

    try
    { 
        if (Action ==   "install") InjectLib (dest);
        if (Action == "uninstall") DeleteLib (dest);

        Echo (LibName + " was successfully " + Action + "ed for " + name + "!");
        
        return 1;
    }
    
    catch (e)
    {
        Echo ("Error, when I was " + Action + "ing " + LibName + " for " + name + ". Make it by your hands :).");
        return 0;
    }        
}

//=============================================================================

function InjectLib (dest)
{
    var Libdest = FS.GetAbsolutePathName (dest + "\\include\\" + LibName);
    Debug ("Ingecting Lib at " + Libdest); 
    
    try
    {
        var f = OpenTextFile (Libdest, "w", true); if (f == null) return;

        f.WriteLine ("#include \"" + LibFolder + "\\" + LibName + "\"");
        
        f.Close();
    }

    catch (e)
    {
        throw Error (e, "Cannot write to " + Libdest);
    }
}

function DeleteLib (dest)
{
    var Libdest = FS.GetAbsolutePathName (dest + "\\include\\" + LibName);
    Debug ("Deleting Lib at " + Libdest); 

    DeleteFile (Libdest, DebugMode);

}

//=============================================================================

function OpenTextFile (file, mode, required)
{
    file = FS.GetAbsolutePathName (file);

    try 
    {
        var f = null;
        if (mode == "r") f = FS.OpenTextFile (file, 1);
        if (mode == "w") f = FS.OpenTextFile (file, 2, true);         

        if (f == null && required) Error ("Cannot open " + file);
        return f;
    }

    catch (e)
    {
        if (required) throw Error (e, "Cannot open " + file);
	return null;
    }
}

//-----------------------------------------------------------------------------

function CopyFile (dest, src)
{
    dest = FS.GetAbsolutePathName (dest);
    src  = FS.GetAbsolutePathName (src);

    try 
    {
        FS.CopyFile (src, dest + "\\");
    }

    catch (e)
    {
        throw Error (e, "Cannot copy " + src + " to " + dest);
    }
}

//-----------------------------------------------------------------------------

function DeleteFile (file, required)
{
    file = FS.GetAbsolutePathName (file);

    try 
    {
        FS.DeleteFile (file);
    }

    catch (e)
    {
        if (required) throw Error (e, "Cannot delete file " + file);
    }
}

//-----------------------------------------------------------------------------

function CreateFolder (folder)
{
    folder = FS.GetAbsolutePathName (folder);

    try 
    {
        FS.CreateFolder (folder);
    }

    catch (e) {}
}

//-----------------------------------------------------------------------------

function Error (e, msg)
    {
    var descr = "";
    if (e != null && 
        e.description != null &&
        e.description != 'undefined' &&
        e.description.length != 0) descr = e.description;

    if (msg != "" && descr != "") msg += ": ";
    msg += descr;

    if (!IgnoreErrors)
       Echo ("ERROR: " + msg + "\n\n" + 
             "Don't be disappointed at this message!" + "\n\n" +
             "Anyway, you may use " + LibName + " without proceeding this setup.");

    return e;
    }

//-----------------------------------------------------------------------------

function Debug (msg)
{
    if (DebugMode) Echo (msg);
}

//-----------------------------------------------------------------------------

function Ask (msg)
{
    var Yes      = 6;
    var No       = 7;
    var YesNo    = 4;
    var Question = 32;

    return Shell.Popup (msg + "    ", 60, "\"" + LibName + " Installer\"", YesNo + Question) == Yes;
}

//-----------------------------------------------------------------------------

function Echo (msg)
{
    var OK          = 0;
    var Information = 64;

    return Shell.Popup (msg + "    ", 10, "\"" + LibName + " Installer\"", OK + Information);
}


