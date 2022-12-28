//https://stackoverflow.com/questions/9907160/how-to-convert-enum-names-to-string-in-c

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,
