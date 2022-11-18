import requests

r = requests.get('http://172.20.241.9/luedataa_kannasta_groupid_csv.php?groupid=85')

with open('D:/School/tietoliikentee_sovellusprojekti_2022/Tietoliikenteen_sovellusprojekti_2022/Python/test.csv', 'w') as f:
    f.write(r.text)