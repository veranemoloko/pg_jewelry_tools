CREATE TYPE jewel_metal_type AS ENUM (
    'gold',
    'silver',
    'platinum'
);


CREATE FUNCTION calculate_metal_weight(
    metal integer,
    purity integer,
    volume float
)
RETURNS float
AS '$libdir/pg_jewelry_tools', 'calculate_metal_weight'
LANGUAGE C STRICT;


CREATE FUNCTION calculate_metal_weight_enum(
    metal jewel_metal_type,
    purity integer,
    volume float
) RETURNS float AS $$
BEGIN
    RETURN calculate_metal_weight(
        CASE metal
            WHEN 'gold' THEN 0
            WHEN 'silver' THEN 1
            WHEN 'platinum' THEN 2
            ELSE NULL
        END,
        purity,
        volume
    );
END;
$$ LANGUAGE plpgsql STRICT;


