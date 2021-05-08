Xvfb :500 -screen 0 1280x1024x24 &
Xvfb :501 -screen 0 1280x1024x24 &
Xvfb :502 -screen 0 1280x1024x24 &
Xvfb :503 -screen 0 1280x1024x24 &
parallel -j 4 DISPLAY=:{2} ./webshazam -s ~/here{1}.png -u 'https://next--storybookjs.netlify.app/official-storybook/iframe.html?id=addons-backgrounds--with-gradient&args=&viewMode=story' ::: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 ::: 500 501 502 503