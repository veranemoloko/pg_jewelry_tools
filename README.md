# pg_jewelry_tools - for now this is learning project 💅


## I researched:
- Creating custom pgSQL functions
- Error handling and edge cases
- Writing automated regression tests

# Installation && Usage
### Build and install
```bash
make && make install
```

### Run tests
```bash
make installcheck
```

# What is there here?
### 💎 Gemstone Calculations
- Converts gemstone weight from carats to grams
- Formula: `grams = carats * 0.2`
- Handles edge cases:
  - Returns NULL for NULL input
  - Throws error for negative values

```sql
SELECT calculate_gemstone_carat_to_gr(5.0); 
SELECT calculate_gemstone_gr_to_carat(2);
```

### 🤘 Metal Calculations

- Supported metals: gold, silver, platinum
- Formula: `weight = (purity / 1000) * weight_mm3`
- Handles edge cases:
    - Returns NULL for any NULL parameter
    - Returns NULL for unknown metal types
```sql
SELECT calculate_metal_weight_gr('gold', 585, 10.0); 
```

## I'm currently working on adding this functionality:
- Implement historical metal price tracking
- Create aggregate functions for batch calculations



