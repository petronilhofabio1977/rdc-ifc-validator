# RDC IFC Validator

Ferramenta determinística de validação IFC baseada em análise textual,
orientada a ação e compatível com CI/CD.

## Modos de validação

- LOOSE (default): tolera drift não estrutural
- STRICT: reprova qualquer divergência de schema

## Exit codes

0 - Aprovado  
1 - Aprovado com alertas  
2 - Reprovado

## Uso

rdc validate arquivo.ifc  
rdc validate-dir pasta/

## Diferenciais

- Sem bibliotecas externas
- Determinismo total
- Relatórios orientados à correção
- Foco em engenharia civil e BIM
