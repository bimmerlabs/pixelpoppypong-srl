@ECHO Off
where /q ymir-sdl3.exe
IF ERRORLEVEL 1 (
    echo "Using project Ymir installation!"
    SET YMIR=../../emulators/Ymir/ymir-sdl3.exe
) else (
    echo "Using system's Ymir installation!"
    SET YMIR=../../emulators/Ymir/ymir-sdl3.exe
)

if not exist ./BuildDrop/*.cue (
    echo "CUE/ISO missing, please build first."
) else (
    @REM Finding first cue file and running it on Ymir
    FOR %%F IN (./BuildDrop/*.cue) DO (
        start %YMIR% -d ./BuildDrop/%%F
        exit /b
    )
)