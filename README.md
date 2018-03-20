## Цель
Создать в ХД новую таблицу "Недолжники".

## Функциональные требования
1. Создать новую таблицу "Недолжники", имеющую одно поле <a href="#">account_id</a> (айди счета). 

   - данные для заполнения - айди счетов клиентов, у которых нет на сегодняшний день просроченной выписки
   - указанную информацию нужно выделить из трех, имеющихся в ХД таблиц:
     ```sh
     - Таблица со счетами кредитных карт (1)
         Состав полей: ID счета
     - Таблица с выписками по кредитным картам (2)
         Состав полей: ID выписки, ID счета, дата выписки, дью_дата, сумма выписки
     - Таблица с платежами клиентов (3)
         Состав полей: ID счета, дата платежа, сумма платежа
     ```
   - алгоритм получения интересующего айди:
     ```sh
     1). для каждого айди счета в таблице (1) выполнить последующие пункты; 
     2). проверить его наличие в таблице (2);
     3). если отсутствует - занести в создаваемую таблицу; 
     4). если присутствует - для последней по дате выписки (относящейся к выбранному айди)
                             запомнить дату и дью-дату и проделать последующие пункты;
                             
     Если дью-дата уже наступила:
     5). в таблице (3) просуммировать платежи по выбранному айди счета в период с даты рассмотренной 
         выписки по сегодняшнее число;       
     6). если полученная сумма >= суммы данной выписки- занести выбранный айди счета в создаваемую таблицу;
         
     Если дью-дата еще не наступила:
     5*). если это единственная (по дью-дате) выписка по выбранному айди счета - занести его в создаваемую 
          таблицу;
     6*). если не единственная (по дью-дате) - рассмотреть предшествующую данной (по дью-дате) выписку,
          выполнив для нее пункты 5 и 6;
     ```
