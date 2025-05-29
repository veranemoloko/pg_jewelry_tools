DROP EXTENSION IF EXISTS pg_jewelry_tools;
CREATE EXTENSION pg_jewelry_tools;

SELECT calculate_gemstone_carat_to_gr(5.0::double precision);
SELECT calculate_gemstone_carat_to_gr(0.2::double precision);
SELECT calculate_gemstone_carat_to_gr(-1.0::double precision);

SELECT calculate_metal_weight_gr('gold'::text, 585, 10.0::double precision);
SELECT calculate_metal_weight_gr('silver'::text, 925, 5.0::double precision);
SELECT calculate_metal_weight_gr('platinum'::text, 950, 3.0::double precision);

SELECT calculate_metal_weight_gr(NULL::text, 585, 10.0::double precision);
SELECT calculate_metal_weight_gr('gold'::text, NULL::int4, 10.0::double precision);
SELECT calculate_metal_weight_gr('gold'::text, 585, NULL::double precision);
