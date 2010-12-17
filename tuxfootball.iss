; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{4F52C42A-023F-4324-B7FC-296C577F75E4}
AppName=Tux Football
AppVersion=0.3.0
;AppVerName=Tux Football 0.3.0
AppPublisher=Tux Football Team
AppPublisherURL=http://tuxfootball.sourceforge.net/
AppSupportURL=http://tuxfootball.sourceforge.net/
AppUpdatesURL=http://tuxfootball.sourceforge.net/
DefaultDirName={pf}\Tux Football
DefaultGroupName=Tux Football
AllowNoIcons=yes
LicenseFile=COPYING
OutputDir=bin
OutputBaseFilename=setup
; SetupIconFile=data\graphics\tuxfootball-setup.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\tuxfootball.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\data\*"; DestDir: "{app}\data"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\jpeg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\libogg-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\libpng12-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\libtiff-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\libvorbis-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\libvorbisfile-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\mikmod.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\SDL_image.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\SDL_mixer.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\SDL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\smpeg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\users\cbrill\Eigene Dateien\source\tuxfootball\tuxfootball-0.3.0\zlib1.dll"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\Tux Football"; Filename: "{app}\tuxfootball.exe"
Name: "{group}\{cm:UninstallProgram,Tux Football}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\Tux Football"; Filename: "{app}\tuxfootball.exe"; Tasks: desktopicon

[Run]
Filename: "{app}\tuxfootball.exe"; WorkingDir: "{app}"; Description: "{cm:LaunchProgram,Tux Football}"; Flags: nowait postinstall skipifsilent

