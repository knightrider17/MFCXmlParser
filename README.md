# MFCXmlParser
Программа с GUI на MFC. Программа "парсер" XML-файлов получает данные из файла, внутри которого находятся данные в формате XML. Внутри файл содержал информацию об "участках" на которых расположены некоторые объекты, датчики и прочее. Все эти данные считываются из файла и показывались внутри интерфейса программы, для возможности удобного редактирования этих файлов.

Программа:

1. Запускается (считав данные из ini-файла)
2. По нажатию на кнопку "Получить Участки" Пытается подключиться к БД используя ODBC-драйвер
3.1. Далее можно выполнить попытку переподключения.
3.2. Или считать данные из локального XML-файла, в котором содержатся данные нужного нам формата
4. После загрузки мы можем редактировать данные внутри файлов-участков, которые по факту имеют внутри структуру XML-файла
5. Редактирование данных внутри программы отражается соответственно и на содержимом XML-файлов

