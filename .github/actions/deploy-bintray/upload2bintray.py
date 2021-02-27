import base64, datetime, json, os, sys
import urllib.request
import urllib.error

subject = os.environ['BINTRAY_SUBJECT']
repo = os.environ['BINTRAY_REPO']
pkg = os.environ['BINTRAY_PACKAGE']
version = os.environ['BINTRAY_VERSION']
username = os.environ['BINTRAY_USER']
key = os.environ['BINTRAY_KEY']

releaseDate = os.environ.get('BINTRAY_RELEASE_DATE')

auth = 'Basic {0}'.format(base64.b64encode('{0}:{1}'.format(username, key).encode('utf-8')).decode('ascii'))

def sendRequest(r, quiet = False):
	try:
		r.add_header('Authorization', auth)
		with urllib.request.urlopen(r) as f:
			content = f.read()
			if not quiet:
				print('< Server replied')
				print(json.dumps(json.loads(content), sort_keys=True, indent=4))
			return content
	except urllib.error.HTTPError as e:
		print('< Server replied')
		print(e)
		sys.exit(1)

for path in sys.argv[1:]:
	filename = os.path.basename(path)

	with open(path, 'rb') as fin:
		print('> Uploading {0} as {1} to Bintray ({2}/{3}/{4} version {5})'.format(path, filename, subject, repo, pkg, version))
		r = urllib.request.Request('https://api.bintray.com/content/{0}/{1}/{2}/{3}/{4}?publish=1'.format(subject, repo, pkg, version, filename), data=fin, method='PUT')
		r.add_header('Content-Type', 'application/octet-stream')
		sendRequest(r)

if releaseDate is not None and len(releaseDate) > 0:
	try:
		releaseDate = datetime.datetime.strptime(releaseDate, '%Y-%m-%dT%H:%M:%S%z')
	except ValueError:
		print('! Skipping invalid release date "{0}"'.format(releaseDate))
		releaseDate = None
	if releaseDate is not None:
		releaseDate = releaseDate.astimezone(datetime.timezone.utc).strftime('%Y-%m-%dT%H:%M:%S.000Z')

		print('> Setting Bintray version release date to {0} ({1}/{2}/{3} version {4})'.format(releaseDate, subject, repo, pkg, version))

		metadata = {'released': releaseDate}
		data = json.dumps(metadata).encode('utf-8')

		r = urllib.request.Request('https://api.bintray.com/packages/{0}/{1}/{2}/versions/{3}'.format(subject, repo, pkg, version), data=data, method='PATCH')
		r.add_header('Content-Type', 'application/json')

		sendRequest(r)
