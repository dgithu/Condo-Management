create or replace procedure spCondoDelete(err_code out integer,
c_condonum in condos.condo_num%type)
as
begin
delete from condos
where condo_num = c_condonum;

err_code:= sql%rowcount;


dbms_output.put_line('Number of rows deleted '||err_code);


exception
when no_data_found THEN
        dbms_output.put_line('Condo with condo number'||c_condonum||'does not exist.');
when others
then
dbms_output.put_line('error');

end spCondoDelete;