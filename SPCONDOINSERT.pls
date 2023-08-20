create or replace procedure spCondoInsert(
err_code out integer,
c_floornum in condos.floor_num%type,
c_condonum in condos.condo_num%type,
c_ownername in condos.ownername%type,
c_condotype in condos.condo_type%type,
c_address in condos.address%type,
c_postalcode in condos.postalcode%type)
as
begin
insert into condos(floor_num,condo_num,ownername,condo_type,address,postalcode)
values(c_floornum,c_condonum,c_ownername,c_condotype,c_address,c_postalcode);


err_code:= sql%rowcount;
commit;

exception
when others
then err_code:= -1;
dbms_output.put_line('Primary key already exits, cannot insert data');
end spCondoInsert;