for i in $(seq 1 20); do 
    ./xvfb-run-safe.sh ./webshazam -d 3 -s ~/here$i.png -u 'https://next--storybookjs.netlify.app/official-storybook/iframe.html?id=addons-backgrounds--with-gradient&args=&viewMode=story'&
done