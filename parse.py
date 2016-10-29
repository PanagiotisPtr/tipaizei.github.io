import bs4 as bs
import urllib.request
import urllib.parse
import webbrowser

sauce = urllib.request.urlopen('http://www.zappit.gr/tv-program').read()

soup = bs.BeautifulSoup(sauce, 'lxml')

rowsLeft = soup.find('div',{'class':'column small-12 medium-6'})

#for row in rowsLeft:
	#channel = row.find('tr').find('span',{'class':'program__channel-name'}).string
	#print(channel)
	#for channel in row.find('table',{'class':'program__table_hor'}):

with open("movies.txt", 'w') as out:

	channels = soup.find_all('span',{'class':'program__channel-name'})
	channelList = []

	for channel in channels:
		#print(channel.string)
		channelList.append(channel.string)

	chnl = ''

	allMovies = []

	for tr in soup.find_all('tr'):
		if tr.find('span', {'class':'program__channel-name'})!=None:
			#print(tr.find('span', {'class':'program__channel-name'}).string)
			chnl = tr.find('span', {'class':'program__channel-name'}).string

		if(chnl=='OTE Cinema 1 HD'):
			break
		for movie in tr.find_all('td', {'class':'movie'}):
			name = movie.find('span',{'class':'program__show'}).find('a').string
			time = movie.find('span',{'class':'program__hour'}).string
			#print(chnl)
			out.write(chnl+'\n')
			#print(time)
			out.write(time+'\n')
			#print(name+'\n')
			out.write(name+'\n')
			allMovies.append(name)

	#print("SCRIPT_END")
	out.write("SCRIPT_END")


searchLinks = []

for mov in allMovies:
	a = str(mov)
	#print(a)
	a = urllib.parse.quote(a, safe='')
	a = a.replace(" ", "+")
	link = "http://www.imdb.com/find?ref_=nv_sr_fn&q=" + a + "&s=all"
	#print(link)
	searchLinks.append(link)

#search IMDb

movieFullNames = []
reviewLinks = []

with open("movieReviews.txt", 'w') as out:
	for link in searchLinks:
		revSauce = urllib.request.urlopen(link).read()
		revSoup = bs.BeautifulSoup(revSauce, 'lxml')
		a = revSoup.find('tr',{'class','findResult odd'})
		if a==None:
			#print("None")
			out.write("None"+'\n')
		else:
			a = a.find('td',{'class','result_text'}).find('a')
			revLink = "http://www.imdb.com" + a['href']
			reviewLinks.append(revLink)
			sweetSauce = urllib.request.urlopen(revLink).read()
			sweetSoup = bs.BeautifulSoup(sweetSauce, 'lxml')
			description = sweetSoup.find('div',{'class':'summary_text'}).text
			description = description.strip()

			if sweetSoup.find('div',{'class':'poster'})!=None:
				thumbnailLink = sweetSoup.find('div',{'class':'poster'}).find('img')
				thumbnailLink = thumbnailLink['src']
				thumbnailLink = thumbnailLink.strip()
			else:
				thumbnailLink = "http://www.cost-ic0803.org/fotografie/foto4.jpg"

			if sweetSoup.find('div',{'class':'ratingValue'})!=None:
				rating = sweetSoup.find('div',{'class':'ratingValue'}).find('span').text
			else:
				rating = "?"

			if sweetSoup.find('time')!=None:
				duration = sweetSoup.find('time').string
				duration = duration.strip()
			else:
				duration = "?h ?m"
			
			fullName = sweetSoup.find('h1').text
			out.write(fullName+'\n')
			out.write(thumbnailLink+'\n')
			out.write(rating+'\n')
			out.write(duration+'\n')
			out.write(description+'\n')
			if sweetSoup.find('div',{'class':'originalTitle'})!=None:
				original = sweetSoup.find('div',{'class':'originalTitle'}).text
				original = original.replace("(original title)","")
				year = ""
				if sweetSoup.find('span',{'id':'titleYear'})!= None:
					year = sweetSoup.find('span',{'id':'titleYear'}).find('a').text
					year = "("+year+")"
				original = original + " " + year
				movieFullNames.append(original)
			else:
				movieFullNames.append(fullName)
		#out.write('NEXT'+'\n')
		out.write('\n')

with open("imdbLinks.txt", 'w') as out:
	for link in reviewLinks:
		out.write(link+'\n')

youtubeLinks = []

for name in movieFullNames:
	name = str(name)
	#print(name)
	name = urllib.parse.quote(name, safe='')
	name = name.replace(" ", "+")
	ytLink = "https://www.youtube.com/results?search_query=" + name + "+Trailer"
	youtubeLinks.append(ytLink)

videoLinks = []
#https://www.youtube.com/embed/4l5eZp8Ae9c
embedLinks = []

for link in youtubeLinks:
	ytSauce = urllib.request.urlopen(link).read()
	ytSoup = bs.BeautifulSoup(ytSauce, 'lxml')
	if ytSoup.find('div',{'class':'yt-lockup-content'})!=None:
		vdLink = ytSoup.find('div',{'class':'yt-lockup-content'}).find('a')['href']
		vdLink = "https://www.youtube.com" + vdLink
		embdlink = "https://www.youtube.com/embed/"+vdLink[-11:]
		embedLinks.append(embdlink)
		videoLinks.append(vdLink)
	else:
		videoLinks.append('#')

with open("movieLinks.txt", 'w') as out:
	for link in embedLinks:
		out.write(link+'\n')


'''

for link in searchLinks:
	revSauce = urllib.request.urlopen(link).read()
	revSoup = bs.BeautifulSoup(revSauce, 'lxml')
	a = revSoup.find('td').find('a')
	if a==None:
		print("None")
	else:
		revLink = "http://www.imdb.com" + a['href']
		sweetSauce = urllib.request.urlopen(revLink).read()
		sweetSoup = bs.BeautifulSoup(sweetSauce, 'lxml')
		description = sweetSoup.find('div',{'class':'summary_text'}).text
		thumbnailLink = sweetSoup.find('div',{'class':'poster'}).find('img')
		thumbnailLink = thumbnailLink['src']
		rating = sweetSoup.find('div',{'class':'ratingValue'}).find('span').text
		duration = sweetSoup.find('time').string
		duration = duration.strip()
		fullName = sweetSoup.find('h1').text
		print(fullName)


'''

print("SUCCESS")

#for movie in soup.find_all('td', {'class':'movie'}):
#	name = movie.find('span',{'class':'program__show'}).find('a').string
#	time = movie.find('span',{'class':'program__hour'}).string
#	if movie.find('span',{'class':'program__show'}).find('a').string == None:
#		print("efwfqwfehejfgadsgfkasgfoyuwfegdo22g3iUY@#$YUU!$U!$IF$!$IU$")
#	print("\n"+time)
#	print(name)

######### WITHOUT WRITING TO FILE ########

'''

for channel in channels:
	#print(channel.string)
	channelList.append(channel.string)

chnl = ''

for tr in soup.find_all('tr'):
	if tr.find('span', {'class':'program__channel-name'})!=None:
		#print(tr.find('span', {'class':'program__channel-name'}).string)
		chnl = tr.find('span', {'class':'program__channel-name'}).string

	if(chnl=='OTE Cinema 1 HD'):
		break
	for movie in tr.find_all('td', {'class':'movie'}):
		name = movie.find('span',{'class':'program__show'}).find('a').string
		time = movie.find('span',{'class':'program__hour'}).string
		print("\n"+chnl)
		print(time)
		print(name)

'''
