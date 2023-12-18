@echo off
set N_SAMPLE=%1%


set cnt=0
for %%a in (%*) do set /a cnt+=1
rem @echo %cnt%

if %cnt% == 0 (
    @echo N is not specified, example: run 10
    goto END1
)

set /a Ndel2=%N_SAMPLE% / 2
set /a Nx2=%N_SAMPLE% * 2

del /q data\*
del /q data_M\*
del /q data_Ndel2\*
del /q data_Nx2\*

md data_N
md data_Ndel2
md data_Nx2


@echo START 3x attempt

@echo %Ndel2%
@echo %Nx2%

call run.cmd %N_SAMPLE%
move /y data\* data_N

call run.cmd %Ndel2%
move /y data\* data_Nd2

call run.cmd %Nx2%
move /y data\* data_Nx2

python spectre_3x.py data_N/signal.txt data_Nd2/signal.txt data_Nx2/signal.txt data_N/signal_noise.txt data_Nd2/signal_noise.txt data_Nx2/signal_noise.txt %1% spectre_3x.png

:END1


@echo END attempts



