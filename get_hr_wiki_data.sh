#!/usr/bin/env/ bash

# korišteni alati:
# wget --version
# 7z --version
# lynx --version
# perl --version
# tr --version
# tar --version

# preuzimanje dumpa kako bi se izbjeglo preoptecenje servera i blaclistanje
echo 'Downloading hr.wiki dump...'
wget https://dumps.wikimedia.org/other/static_html_dumps/current/hr/wikipedia-hr-html.tar.7z

# extract preuzetog dumpa
echo 'Extracting hr.wiki dump...'
mkdir hr_wiki
7z x -so wikipedia-hr-html.tar.7z | tar xf - -C ./hr_wiki

FNAME="combined.txt"

# parsiranje i spajanje teksta iz html datoteka u jednu datoteku
# konverzija slova u mala slova
shopt -s globstar
for page in **/*.html; do
	echo "Parsing: ${page}"
	lynx -dump -nolist ${page} | tr '[:upper:]' '[:lower:]' >> ${FNAME}
done

echo 'Removing chars different from [a-z]...'
# ascii a-z znakove - u jednom redu
perl -pi -e 's/[^a-z]+/ /g' ${FNAME}

# uklanjanje svih rijeci koje sadrze slova koja nisu dio hrvatske abecede
sed -i 's/[^ ]*x[^ ]*//ig' ${FNAME}
sed -i 's/[^ ]*y[^ ]*//ig' ${FNAME}
sed -i 's/[^ ]*w[^ ]*//ig' ${FNAME}
sed -i 's/[^ ]*q[^ ]*//ig' ${FNAME}

