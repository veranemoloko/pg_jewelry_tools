CREATE TYPE gemstone AS (
    name        TEXT,       
    carat       FLOAT,    
    clarity     TEXT,      
    color       TEXT,
    cost_price  FLOAT        
);

CREATE TYPE precious_metal AS (
    type        TEXT,       
    purity      INT,            
    weight_gr   FLOAT,
    cost_price  FLOAT           
);

CREATE TYPE jw_item AS (
    gems        gemstone[],    
    metal       precious_metal, 
    item_type   TEXT,
    cost_price  FLOAT 
);


CREATE OR REPLACE FUNCTION calculate_gemstone_gr_to_carat(
    carat double precision
)
RETURNS double precision
AS '$libdir/pg_jewelry_tools', 'calculate_gemstone_gr_to_carat'
LANGUAGE C STRICT;


CREATE OR REPLACE FUNCTION calculate_gemstone_carat_to_gr(
    carat double precision
)
RETURNS double precision
AS '$libdir/pg_jewelry_tools', 'calculate_gemstone_carat_to_gr'
LANGUAGE C STRICT;


CREATE OR REPLACE FUNCTION calculate_metal_weight_gr(
    metal TEXT,
    purity INTEGER,
    volume_mm3 double precision
)
RETURNS double precision
AS '$libdir/pg_jewelry_tools', 'calculate_metal_weight_gr'
LANGUAGE C STRICT;


CREATE OR REPLACE FUNCTION public.test_add_one(i integer)
RETURNS integer
LANGUAGE sql
AS $$
    SELECT i + 1;
$$;
