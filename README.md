# transport-catalogue
Транспортный каталог автобусных маршрутов.
[Ссылка на схемы](https://docs.google.com/presentation/d/1be_NCfvZYFI-WV7DG5G0qvFMbXcnTXSk8U_aji_lDxU/edit?usp=sharing).

## Хранение данных
### Хранение остановок
![Схема хранения остановок](https://github.com/qvabrik/transport-catalogue/blob/main/readme_imgs/stops_.jpg)
- Данные каждой остановки хранятся в `struct Stop`, которая содержит поля *name*, *lantitude*, *longitude*;
- Остановки хранятся в контейнере `std::deque<Stop> stops_`;
- Для быстрого поиска данных остановки по названию предусмотрен контейнер `std::unordered_map<std::string_view, Stop*> stopname_to_stopdata_`, валидность указателей обеспечена выбором контейнера deque для хранения stops_.
  

### Хранение маршрутов
![Схема хранения маршрутов](https://github.com/qvabrik/transport-catalogue/blob/main/readme_imgs/buses_.jpg)
- Данные каждого маршрута хранятся в `struct Bus`, которая содержит поля *name*, *route*, *is_circle*.  Указатели на остановки маршрута хранятся в векторе *route*, валидность указателей обеспечена выбором контейнера deque для хранения stops_.
- Для быстрого поиска данных маршрута по названию предусмотрен контейнер `std::unordered_map<std::string_view, Bus*> busname_to_busdata_`, валидность указателей обеспечена выбором контейнера deque для хранения buses_.

## Взаимодействие с сервером
### Загрузка данных
#### AddStop
Загрузка остановки на сервер.
Сигнатура функции: Stop& AddStop(std::string&& name, double latitude, double longtitude);
Метод принимает имя и координаты остановки, и далее:
1. Перемещает структуру Bus, созданную из полученных значений, в stops_;
2. Помещает string_view на имя остановки и указатель на данные в stopname_to_stopdata_;
3. Возвращает ссылку на данные остановки.
#### AddBus
Загрузка автобуса на сервер.
Сигнатура функции: Bus& AddBus(std::string&& name, std::vector<std::string>&& stops_names);
Метод принимает значение и вектор имён остановок и далее:
1. Определяет, кольцевой маршрут или нет;
2. Строит вектор с указателями на остановки маршрута в порядке их прохождения;
3. Перемещает (move) в buses_ структуру Bus, созданную из имени, вектора указателей установок и маркера кольцевого маршрута;
4. Помещает в busname_to_busdata_ string_view на имя маршрута и указатель на его данные;
5. Возвращает ссылку на данные маршрута. 
### Получение данных
#### FindStop
#### FindBus
#### GetBusInfo
