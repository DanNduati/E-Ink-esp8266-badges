const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>E-Ink ESP8266-12E badges</title>
  <style>
    body{
      background-color: #EEEEEE;
    }
    h1 {
      text-align: center;
      font-family: Monospace;
      font-size: 50px;
    }
    ul {
      list-style: none;
      padding: 0;
    }
    table{
      margin: 0 auto;
      text-align: center;
    }
    li{ 
      font-family: sans-serif;
      text-align: center;
      font-size: 30px;
      padding: 5px 10px;
        background-color: #EEEEEE;
      }
    table, th, td {
      border: 1px solid black;
      border-collapse: collapse;
    }
    th{
      font-size: 20px;
    }
    th, td {
      padding: 15px;
    }
  </style>
</head>
<body>
  <h1> Special Messages</h1>
  <table>
    <tr>
      <th>Special Message</th>
      <th>Status</th>
    </tr>
    <tr>
      <td>BIC_FOUNDED_2018</td>
      <td>0</td>
    </tr>
    <tr>
      <td>7h3_f0und3r_h45_4n_3v1l_7w1n</td>
      <td>0</td>
    </tr>
    <tr>
      <td>MK48</td>
      <td>0</td>
    </tr>
    <tr>
      <td>y0ur_f4v0r173_4cc3550ry_1s_Socks!</td>
      <td>0</td>
    </tr>
  </table>
  <h1> Never Forgotten </h1>
  <ul>
    <li>Cras justo odio</li>
    <li>Winston Smith</li>
    <li>Ronald Greene</li>
    <li>Andrew Brown </li>
    <li>Ma’Khia Bryant</li>
    <li>Daunte Wright</li>
    <li>Jacob Blake</li>
    <li>Priscilla Slatter</li>
    <li>Elijah McClain</li>
    <li>Dominique Fells</li>
    <li>Jamel Floyd</li>
    <li>David McAtee</li>
    <li>Justin Howell</li>
    <li>Tony McDade</li>
    <li>Regis Korchinski-Paquet</li>
    <li>George Floyd</li>
    <li>Yassin Mohamed</li>
    <li>Finan A. Berhe</li>
    <li>Sean Reed</li>
    <li>Joel Acevedo</li>
    <li>Michael Ramos</li>
    <li>Steven Taylor</li>
    <li>Daniel Prude</li>
    <li>Breonna Taylor</li>
    <li>Manuel Ellis</li>
    <li>Ahmaud Arbery</li>
    <li>Darius Tarver</li>
    <li>Alvin Cole</li>
    <li>William Green</li>
    <li>Kwam Jones</li>
    <li>Jamee Johnson</li>
    <li>Michael Dean</li>
    <li>Ariane McCree</li>
    <li>Christopher Whitefield</li>
    <li>Atatiana Koquice Jefferson</li>
    <li>Derishia Blackwell</li>
    <li>Devon Bailey</li>
    <li>Eric Logan</li>
    <li>Ty’Rese West</li>
    <li>Brandon Webber</li>
    <li>JaQuavion Slaton</li>
    <li>Ryan Twyman</li>
    <li>Miles Hall</li>
    <li>Crystal Ragland</li>
    <li>Pamela Turner</li>
    <li>Nina Adams</li>
    <li>Latohsa Walton</li>
    <li>Brittany McLean</li>
    <li>Willie McCoy   </li>
    <li>Jimmy Atchinson</li>
    <li>D’ettrick Griffon</li>
    <li>Angel Decarlo</li>
    <li>April Webster</li>
    <li>Tameka Simpson</li>
    <li>Emantic Bradford </li>
    <li>Jemel Roberson</li>
    <li>Charles Roundtree </li>
    <li>LaJuana Philips</li>
    <li>Chinedu Okobi</li>
    <li>DeAndre Ballard</li>
    <li>Botham Jean</li>
    <li>O’Shae Terry</li>
    <li>Cynthia Fields</li>
    <li>Antwon Rose</li>
    <li>Robert White</li>
    <li>LaShanda Anderson</li>
    <li>Shukri Said</li>
    <li>Stephon Clark</li>
    <li>DeCynthia Clements</li>
    <li>Adam Trammell</li>
    <li>Saheed Vassel</li>
    <li>Crystalline Barnes</li>
    <li>Geraldine Townsend</li>
    <li>Aaron Bailey</li>
    <li>Charleena Lyles</li>
    <li>TheFetusOf CharleenaLyles</li>
    <li>Terry Williams</li>
    <li>Jordan Edwards</li>
    <li>Chad Robertson</li>
    <li>Deborah Danner</li>
    <li>Alfred Olango</li>
    <li>Terrence Crutcher</li>
    <li>Tyree King</li>
    <li>Terrence Sterling</li>
    <li>Sylville Smith</li>
    <li>Jamarion Robinson</li>
    <li>Korryn Gains</li>
    <li>Joseph Curtis Mann</li>
    <li>Jay Anderson</li>
    <li>Philando Castile</li>
    <li>Alton Sterling</li>
    <li>Delrawn Small</li>
    <li>Samuel Mallard</li>
    <li>Keith Childress </li>
    <li>Bettie Jones</li>
    <li>Quintonio LeGreir</li>
    <li>Kevin Mathews</li>
    <li>Michael Noel</li>
    <li>Leroy Browning</li>
    <li>Roy Lee Nelson</li>
    <li>Miguel Espinal</li>
    <li>Mario Woods</li>
    <li>Tiara Thomas</li>
    <li>Cornelius Brown</li>
    <li>Jamar O’Neal Clark</li>
    <li>Richard Perkins</li>
    <li>Michael Marshall</li>
    <li>Nathanial Pickett</li>
    <li>Alonzo Smith</li>
    <li>Anthony Ashford</li>
    <li>Dominic Hutchinson</li>
    <li>Lamontez Jones</li>
    <li>Corey Jones</li>
    <li>Rayshaun Cole</li>
    <li>Paterson Brown</li>
    <li>Christopher Kimble</li>
    <li>Junior Prosper</li>
    <li>Jeremy McDole</li>
    <li>Kieth McLeod</li>
    <li>Wayne Wheeler</li>
    <li>India Kager</li>
    <li>Lavante Biggs</li>
    <li>Felix Kumi</li>
    <li>Asshams Manley</li>
    <li>Christian Taylor</li>
    <li>Brian Day</li>
    <li>Michael Sabbie</li>
    <li>Samuel DuBose</li>
    <li>BillyRay Davis</li>
    <li>Johnathan Sanders</li>
    <li>Albert Joseph Davis</li>
    <li>Darrius Stewart</li>
    <li>Sandra Bland</li>
    <li>Salvado Ellswood</li>
    <li>Joseph Mann</li>
    <li>Victor Larosa</li>
    <li>Spencer McCain</li>
    <li>Zamiel Crawford</li>
    <li>Jermaine Benjamin</li>
    <li>Kevin Higgenbotham</li>
    <li>Kris Jackson</li>
    <li>Ross Anthony</li>
    <li>Richard Davis</li>
    <li>Curtis Jordan</li>
    <li>Markus Clark</li>
    <li>Lorenzo Hayes</li>
    <li>De’Angelo Stallworth</li>
    <li>Dajaun Graham</li>
    <li>Reginald Moore</li>
    <li>Nuwah Laroche</li>
    <li>Jason Champion</li>
    <li>Bryan Overstreet</li>
    <li>Brendon Glenn</li>
    <li>Alexia Christian</li>
    <li>David Felix</li>
    <li>Terry Chatman</li>
    <li>William Chapman </li>
    <li>Samuel Harnell</li>
    <li>Norman Cooper</li>
    <li>Freddie Gray</li>
    <li>Frank Shepard</li>
    <li>Walter Scott</li>
    <li>Donald Ivy</li>
    <li>Eric Harris</li>
    <li>Phillip White</li>
    <li>Mya Hall</li>
    <li>Jason Moland</li>
    <li>Meagan Hockaday</li>
    <li> Bobby Gross</li>
    <li>Terrance Moxley</li>
    <li>Anthony Hill</li>
    <li>Tony Robinson</li>
    <li>Bernard Moore</li>
    <li>Naeschylus Carter-Vinzant</li>
    <li>Tony Robinson</li>
    <li>Charly Keunan</li>
    <li>Janisha Fonville</li>
    <li>Natasha Mckenna</li>
    <li>Frank Smart</li>
    <li>Kevin Davis</li>
    <li>Jerame C. Reid</li>
    <li>Rumain Brisbon</li>
    <li>Tamir Rice</li>
    <li>Akai Gurley</li>
    <li>Tanisha Anderson</li>
    <li>Laquan McDonald</li>
    <li>Kajieme Powell</li>
    <li>Michelle Cusseaux</li>
    <li>Dante Parker</li>
    <li>Ezell Ford</li>
    <li>Michael Brown</li>
    <li>John Crawford</li>
    <li>Eric Garner</li>
    <li>Dontre Hamilton</li>
    <li>Victor White </li>
    <li>Gabriella Nevarez</li>
    <li>Yvette Smith</li>
    <li>McKenzie Cochran</li>
    <li>Jordan Baker</li>
    <li>Gregory Hill</li>
    <li>Andy Lopez</li>
    <li>Miriam Carey</li>
    <li>Barrington Williams</li>
    <li> Johnathan Ferrell</li>
    <li>Carlos Alcis</li>
    <li>Larry Jackson</li>
    <li>Kyam Livingston</li>
    <li>Terrance Franklin</li>
    <li>Clinton Allen</li>
    <li>Kimani Gray</li>
    <li>Kayla Moore</li>
    <li>Jamaal Moore</li>
    <li>Shelly Frey</li>
    <li>Darnisha Harris</li>
    <li>Malissa Williams</li>
    <li>Timothy Russell</li>
    <li>Noel Palanco</li>
    <li>Reynaldo Cuevas</li>
    <li>Chavis Carter</li>
    <li>Alesia Thomas</li>
    <li>Shantel Davis</li>
    <li>Sharmel Edwards</li>
    <li>Tamon Robinson</li>
    <li>Ervin Jefferson</li>
    <li>Kendrec McDade</li>
    <li>Rekia Boyd</li>
    <li>Shereese Francis</li>
    <li>Jersey Green</li>
    <li>Wendell  Allen</li>
    <li>Nehemiah Dillard</li>
    <li>Dante Price</li>
    <li>Raymond Allen</li>
    <li>Trayvon Martin</li>
    <li>Johnnie Warren</li>
    <li>Manual Loggins</li>
    <li>Ramarley Graham</li>
    <li>Anthony Smith</li>
    <li>Kenneth Chamberlain </li>
    <li>Alonzo Ashley</li>
    <li>Derek Williams</li>
    <li>Raheim Brown</li>
    <li>Reginald Doucet</li>
    <li>Derrick Jones</li>
    <li>Danroy Henry</li>
    <li>Tony Bean</li>
    <li>Aiyana Stanley-Jones</li>
    <li>Steven Washington</li>
    <li>Aaron Campbell</li>
    <li>Kiwane Carrington</li>
    <li>Victor Steen</li>
    <li>Shem Walker</li>
    <li>Oscar Grant</li>
    <li>Tarika Wilson</li>
    <li>DeAunta Farrow</li>
    <li>Sean Bell</li>
    <li>Kathryn Johnston</li>
    <li>James Brissette</li>
    <li>Jose Homles</li>
    <li>Leanord Bartholomew</li>
    <li>Lesha Bartholemew</li>
    <li>Ronald Madison</li>
    <li>Susan Bartholemew</li>
    <li>Henry Glover</li>
    <li>Timothy Stansbury</li>
    <li>Ousmane Zongo</li>
    <li>Alberta Spruill</li>
    <li> Justin Fields</li>
    <li>Kendra James</li>
    <li>Orlando Barlow</li>
    <li>Nizah Morris</li>
    <li>Larry Jenkins</li>
    <li>Timothy Thomas</li>
    <li>Ronald Beasley</li>
    <li>Earl Murray</li>
    <li>Prince Jones</li>
    <li>Patrick Dorismond</li>
    <li>Malcolm Ferguson</li>
    <li>LaTanya Haggerty</li>
    <li>Margaret Mitchell</li>
    <li>Amadou Diallo</li>
    <li>Tyisha Miller</li>
    <li>Abner Louima</li>
    <li>Dannette Daniels</li>
    <li>Frankie Perkins</li>
    <li>Nicholas Heyward</li>
    <li>Sonji Taylor</li>
    <li>Malice Green</li>
    <li>Mary Mitchell</li>
    <li>Rodney King</li>
    <li>Yvonne Smallwood</li>
    <li>Eleanor Bumpurs</li>
    <li>Michael Stewart</li>
    <li>Eula Love</li>
    <li>Arthur Miller </li>
    <li>Randolph Evans</li>
    <li>Barry Evans</li>
    <li>Rita Loyd</li>
    <li>Henry Dumas"
  </ul>
</body>
</html>
)=====";
