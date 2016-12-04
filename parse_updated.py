import bs4 as bs
import urllib.request
import urllib.parse
import webbrowser

sauce = urllib.request.urlopen('http://tv.pathfinder.gr/movies').read()

soup = bs.BeautifulSoup(sauce, 'lxml').find('table', {'cellspacing':'1'})

moviesEven = soup.find_all('tr', {'class':'even'})
moviesOdd = soup.find_all('tr', {'class':'odd'})

allMovies = []

times = []
movieNames = []
channels = []
for movie in moviesEven:
	stats = movie.find_all('td') # 1 --> Time, 2--> Movie, 3 --> Channel
	times.append(stats[1].text)

for movie in moviesEven:
	stats = movie.find_all('td') # 1 --> Time, 2--> Movie, 3 --> Channel
	movieNames.append(stats[2].text.title())

for movie in moviesEven:
	stats = movie.find_all('td') # 1 --> Time, 2--> Movie, 3 --> Channel
	channels.append(stats[3].text)

for movie in moviesOdd:
	stats = movie.find_all('td') # 1 --> Time, 2--> Movie, 3 --> Channel
	times.append(stats[1].text)

for movie in moviesOdd:
	stats = movie.find_all('td') # 1 --> Time, 2--> Movie, 3 --> Channel
	movieNames.append(stats[2].text.title())

for movie in moviesOdd:
	stats = movie.find_all('td') # 1 --> Time, 2--> Movie, 3 --> Channel
	channels.append(stats[3].text)

with open("movies.txt", 'w') as out:

	for i in range(0,len(times)):
		out.write(channels[i]+'\n')
		out.write(times[i]+'\n')
		out.write(movieNames[i]+'\n')
		allMovies.append(movieNames[i])

	out.write('SCRIPT_END')
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

print("SUCCESS")