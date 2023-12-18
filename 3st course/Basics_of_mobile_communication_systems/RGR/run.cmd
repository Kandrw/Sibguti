@echo off

set FILE_DATA=data/data.bin
set FILE_DATA_TXT=data/data.txt

set FILE_DATA_CRC=data/data_crc.bin
set FILE_DATA_CRC_TXT=data/data_crc.txt
set FILE_GOLD_DATA_CRC=data/gold_data_crc.bin
set FILE_BIT_STR=data/gold_data_crc.txt
set FILE_SAMPLE=data/sample.txt
set N_SAMPLE=%1%
set POS_SIG=200
set FILE_SIGNAL=data/signal.txt
set FILE_SIGNAL_NOISE=data/signal_noise.txt
set FILE_SEQ_GOLD_TXT=data/seq_gold_start.txt
set FILE_SEQ_GOLD_END_TXT=data/seq_gold_end.txt
set FILE_RECV_DATA_CRC_TXT=data/recv_data_crc.txt
set FILE_RECV_DATA_CRC=data/recv_data_crc.bin
set U_VALUE=0.0
set Q_VALUE=0.2

set cnt=0
for %%a in (%*) do set /a cnt+=1
rem @echo %cnt%

if %cnt% == 0 (
    @echo N is not specified, example: run 10
    goto END1
)
@echo START

del *.exe
rem goto END1

del /q data\*
del /q img\*
md data
mingw32-make SRC="bytes_to_str.c operation_bit.c" PROGRAM=bytes_to_str CC=gcc FORMAT="c"
mingw32-make SRC="item1.c operation_bit.c" PROGRAM=item1
mingw32-make SRC="add_gold_sequence.cpp operation_bit.c" PROGRAM=add_gold_seq CC=g++ FORMAT="cpp c"
mingw32-make SRC="calc_CRC.c operation_bit.c" PROGRAM=calc_CRC
mingw32-make SRC="generate_samples.c operation_bit.c" PROGRAM=generate_samples
mingw32-make SRC="create_signal_array.c operation_bit.c" PROGRAM=create_signal_array
mingw32-make SRC="calc_CRC.c operation_bit.c" PROGRAM=only_calc_CRC VAR="-DONLY_CALC_CRC=1"
rem Ввод данных
item1.exe %FILE_DATA%
rem биты в строку
bytes_to_str.exe %FILE_DATA% %FILE_DATA_TXT%
python graph_with_data.py %FILE_DATA_TXT% img/fig_data_input.png "Input data"
rem Подсчет корреляции
calc_CRC.exe %FILE_DATA% %FILE_DATA_CRC%
bytes_to_str.exe %FILE_DATA_CRC% %FILE_DATA_CRC_TXT%
rem Добавление синхро-последовательности
add_gold_seq.exe %FILE_GOLD_DATA_CRC% %FILE_DATA_CRC% %FILE_SEQ_GOLD_TXT% %FILE_SEQ_GOLD_END_TXT%
rem биты в строку
bytes_to_str.exe %FILE_GOLD_DATA_CRC% %FILE_BIT_STR%
python graph_with_data.py %FILE_BIT_STR% img/fig_Gold_data_crc.png "sequnce Gold + data + CRC"
rem Генерация отсчетов
generate_samples.exe %FILE_GOLD_DATA_CRC% %N_SAMPLE% %FILE_SAMPLE%
python graph_with_data.py %FILE_SAMPLE% img/fig_sample.png
rem Создание сигнала( 2xN)
create_signal_array.exe %FILE_SAMPLE% %POS_SIG% %FILE_SIGNAL%
python graph_with_data.py %FILE_SIGNAL% img/fig_signal.png "Signal"

rem Генерация шума
python gen_noise.py %FILE_SIGNAL% %U_VALUE% %Q_VALUE% %FILE_SIGNAL_NOISE% img/fig_noise.png
rem Синхронизация
rem python calc_correlation.py %FILE_SIGNAL_NOISE% %FILE_SEQ_GOLD_TXT% %FILE_SEQ_GOLD_END_TXT% img/fig6.png img/fig7.png img/fig8.png %FILE_RECV_DATA_CRC_TXT% 
python calc_correlation.py %FILE_SIGNAL_NOISE% %FILE_SEQ_GOLD_TXT% %FILE_SEQ_GOLD_END_TXT% %N_SAMPLE% img/fig_correlation_start.png img/fig_end.png img/fig_sample.png %FILE_RECV_DATA_CRC_TXT% 

rem Строковые биты в биты
python str_bytes_to_bytes.py %FILE_RECV_DATA_CRC_TXT% %FILE_RECV_DATA_CRC%
rem Проверка crc, декодирование данных
only_calc_CRC.exe %FILE_RECV_DATA_CRC%
rem Сравнение принятых и отправленных данных
python cmp_recv_data_and_send_data.py %FILE_RECV_DATA_CRC_TXT% %FILE_DATA_CRC_TXT% no_show
rem Спектры сигналов
python spectre.py %FILE_SIGNAL% %FILE_SIGNAL_NOISE% img/fg_spectre.png

rem Вывести все графики 
rem python output_graphs.py img
:END1
@REM generate_samples.exe %FILE_GOLD_DATA_CRC% %N_SAMPLE% %FILE_SAMPLE%



@echo END
