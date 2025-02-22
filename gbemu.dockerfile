FROM  node:22-bullseye

WORKDIR /build
COPY ./package.json .
COPY ./package-lock.json .
RUN npm ci
COPY . .
COPY .git .
RUN npm run docs:generate-release-notes
RUN npm run build

FROM scratch
COPY --from=0 /build/dist /dist
