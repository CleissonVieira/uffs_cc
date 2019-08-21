create table PageRevision(
  name varchar,
  data date, 
  author varchar, 
  texto text
);

create table PageAudit(
  name varchar, 
  data date, 
  dif_len integer,
  usuario text,
  texto text
);

insert into PageRevision values ('Teste1', '1987-07-25', 'Autor1', 'Texto1');
insert into PageRevision values ('Teste2', '1954-09-20', 'Autor2', 'Texto2');

create or replace function auditor() returns trigger as $$
  declare
    x integer;
  begin 
    x = length(OLD.texto) - length(NEW.texto);
    insert into PageAudit values (NEW.name, now(), x, current_user, NEW.texto);
    return null;
  end; 
$$ language plpgsql;

create trigger manter_audit
after update on PageRevision
for each row execute procedure auditor();

update PageRevision set texto = 'deu certo2' where name = 'Teste2';

