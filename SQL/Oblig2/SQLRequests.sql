--1 

select kundenr, navn, telefonnr1 as "telefonnr", epost, fakturaadrgate, fakturaadrgatenr, fakturaadrpostnr from kunde

--2 

select o.utleiddato, c.kundenr, o.utstyrsid,  u.merke, u.modell, u.type from utstyr as u, kunde as c, kundebehandler as k, orders as o where k.kundebehandlernr = o.kundebehandlernr and k.kundebehandlernavn like "berit hansen" and o.innlevertdato is null and c.kundenr = o.kundenr and u.utstyrsid = o.utstyrsid 

--3 

select * from orders where orders.utleiddato >= '2019-01-01' and orders.innlevertdato <= '2020-02-10' 

--4 

select u.utstyrsid as "utstyrsmal_id", if(o.leveringskostnad is null, sum(o.betalt), sum(o.betalt)-o.leveringskostnad) as "sumperutstyr 1", u.merke as "utstyrsmerke", u.modell as "utstyrsmodell", u.type as "utstyrstype" from orders as o, utstyr as u where u.utstyrsid = o.utstyrsid and o.betalt is not null group by u.utstyrsid order by if(o.leveringskostnad is null, sum(o.betalt), sum(o.betalt)-o.leveringskostnad) desc 

--5 

select count(o.utstyrsid) as "antutleid", u.merke as "utstyrsmerke", u.modell as "utstyrsmodell", u.type as "utstyrstype", u.kategori from orders as o, utstyr as u where o.utstyrsid = u.utstyrsid group by o.utstyrsid limit 1 