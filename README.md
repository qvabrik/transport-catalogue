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
- Данные каждого маршрута хранятся в `struct Bus`, которая содержит поля *name*, *route*.  Указатели на остановки маршрута хранятся в векторе *route*, валидность указателей обеспечена выбором контейнера deque для хранения stops_.
- Для быстрого поиска данных маршрута по названию предусмотрен контейнер `std::unordered_map<std::string_view, Bus*> busname_to_busdata_`, валидность указателей обеспечена выбором контейнера deque для хранения buses_.

## Взаимодействие с сервером
### Загрузка данных
### Получение данных
