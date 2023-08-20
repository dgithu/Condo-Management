create or replace procedure spCondoSelect(
err_code out integer,
c_floornum out condos.floor_num%type,
c_condonum in condos.condo_num%type,
c_ownername out condos.ownername%type,
c_condotype out condos.condo_type%type,
c_address out condos.address%type,
c_postalcode out condos.postalcode%type)
as
begin
select floor_num,ownername,condo_type,address,postalcode
into c_floornum,c_ownername,c_condotype,c_address,c_postalcode
from condos
where condo_num = c_condonum;

dbms_output.put_line('Floor num : '||c_floornum);
dbms_output.put_line('Ownername : '||c_ownername);
dbms_output.put_line('Condo Type: '||c_condotype);
dbms_output.put_line('Address   : '||c_address);
dbms_output.put_line('PostalCode: '||c_postalcode);


err_code:= sql%rowcount;

exception
when others
then err_code:= -1;
dbms_output.put_line('No condo found');

end spCondoSelect;